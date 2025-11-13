/*
 * Copyright 2021 Lor Worwag,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Purpose: This file loads the Home screen after authenticate user. This file
 * contains actions that allow user to scan barcodes and display specific barcode
 * related data.
 *
 * This app includes Sign-In, Sign-Up functionalities. It can scan food
 * products' barcodes and display relative barcode data. Data is communicated
 * through Firebase Real-Time Database.
 *
 * @author Lor Worwag lor.worwag@gmail.com
 *
 * @version Mar, 2021
 */

import CodeScanner
import SwiftUI
import Firebase

struct HomeView: View {
    @StateObject var router: Router
    @StateObject var barcodeVM = BarcodeScanViewModel()
    @State var isPresented = false
    @State var scannedCode: String?
    
    var body: some View {
        NavigationView {
            VStack {
                Text("You are in Home Screen Now!")
                    .padding()
                Button("Scan Code") { self.isPresented = true }
                    .sheet(isPresented: $isPresented) { self.scannerSheet }
                    .alert(isPresented: $barcodeVM.barcodeNotFoundAlert) {
                        Alert(title: Text("Barcode Not Found"), message: Text("Sorry! No data for current barcode."))
                    }
                Spacer()
                
                if scannedCode != nil, barcodeVM.barcodeData != nil {
                    DisplayBarcodeInfo(scannedCode: self.scannedCode, barcodeVM: barcodeVM)
                }
                Spacer()
            }
            .navigationTitle(Text("Home"))
            .navigationBarTitleDisplayMode(.inline)
            .navigationBarItems(trailing: Button("Setting") {
                withAnimation(.default) {
                    router.currentPage = .SettingPage
                }
            })
        }
    }
    
    var scannerSheet: some View {
        CodeScannerView(
            codeTypes: [.ean8, .ean13, .pdf417],
            completion: { result in
                if case let .success(code) = result {
                    self.scannedCode = code
                    DispatchQueue.main.async {
                        self.barcodeVM.getData(scannedCode: code)
                    }
                    self.isPresented = false
                }
            }
        )
    }
}

struct DisplayBarcodeInfo: View {
    var scannedCode: String?
    @StateObject var barcodeVM: BarcodeScanViewModel

    var body: some View {
        List {
            Section(header: Text("Basic Info")) {
                Text("\(barcodeVM.barcodeData!.productName)")
                Text("Barcode No.: \(scannedCode!)")
            }
            
            Section(header: Text("Ingredients")) {
                ForEach(barcodeVM.barcodeData!.ingredients, id: \.self) { item in
                    Text(item)
                }
            }
            
            Section(header: Text("Nutrition Facts")) {
                Text("Cholesterol: \(barcodeVM.barcodeData!.nutritionFacts.cholesterol)")
                Text("Cholesterol Percentage: \(barcodeVM.barcodeData!.nutritionFacts.cholesterolPercentage)")
                Text("Protein: \(barcodeVM.barcodeData!.nutritionFacts.protein)")
                Text("Protein Percentage: \(barcodeVM.barcodeData!.nutritionFacts.proteinPercentage)")
                Text("Sodium: \(barcodeVM.barcodeData!.nutritionFacts.sodium)")
                Text("Sodium Percentage: \(barcodeVM.barcodeData!.nutritionFacts.sodiumPercentage)")
                Text("Total Carbohydrate: \(barcodeVM.barcodeData!.nutritionFacts.totalCarbohydrate)")
                Text("Total Carbohydrate Percentage: \(barcodeVM.barcodeData!.nutritionFacts.totalCarbohydratePercentage)")
                Text("Total Fat: \(barcodeVM.barcodeData!.nutritionFacts.totalFat)")
                Text("Total Fat Percentage: \(barcodeVM.barcodeData!.nutritionFacts.totalFatPercentage)")
            }
        }
    }
}

// MARK:- View Models

class BarcodeScanViewModel: ObservableObject {
    @Published var barcodeData: BarcodeTemplate?
    @Published var barcodeNotFoundAlert = false
    
    func getData(scannedCode: String) {
        var ref: DatabaseReference!
        ref = Database.database().reference()
        
        ref.child("barcodes").child(scannedCode).getData { (error, snapshot) in
            if let error = error {
                print("Error getting data \(error)")
            }
            else if snapshot.exists() {
                guard let data = try? JSONSerialization.data(withJSONObject: snapshot.value! as Any, options: []) else { return }
                print("snapshot: \(snapshot.value!)")
                DispatchQueue.main.sync {
                    self.barcodeData = try? JSONDecoder().decode(BarcodeTemplate.self, from: data)
                }
                print("code from VM: \(scannedCode)")
            }
            else {
                DispatchQueue.main.sync {
                    self.barcodeNotFoundAlert = true
                }
                print("No data available")
                print("scanned code: \(scannedCode)")
            }

        }
    }
}

// MARK:- Templates

struct BarcodeTemplate: Codable, Identifiable {
    var id: String
    var productName: String
    var ingredients: [String]
    var nutritionFacts: NutritionFactsTemplate
}

struct NutritionFactsTemplate: Codable {
    var cholesterol: String
    var cholesterolPercentage: String
    var protein: String
    var proteinPercentage: String
    var sodium: String
    var sodiumPercentage: String
    var totalCarbohydrate: String
    var totalCarbohydratePercentage: String
    var totalFat: String
    var totalFatPercentage: String
}



struct HomeView_Previews: PreviewProvider {
    static var previews: some View {
        HomeView(router: Router())
    }
}
