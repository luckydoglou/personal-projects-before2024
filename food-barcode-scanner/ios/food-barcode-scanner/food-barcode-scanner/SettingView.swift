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
 * Purpose: This file loads the Setting screen. This file contains actions
 * that allow user to sign out of the app.
 *
 * This app includes Sign-In, Sign-Up functionalities. It can scan food
 * products' barcodes and display relative barcode data. Data is communicated
 * through Firebase Real-Time Database.
 *
 * @author Lor Worwag lor.worwag@gmail.com
 *
 * @version Mar, 2021
 */

import SwiftUI
import Firebase

struct SettingView: View {
    @StateObject var router: Router
    
    var body: some View {
        NavigationView {
            VStack {
                Text("You are in Setting Screen Now!")
                    .padding()
                Button("Sign Out") {
                    signOut()
                }
            }
            .navigationTitle(Text("Setting"))
            .navigationBarTitleDisplayMode(.inline)
            .navigationBarItems(leading: Button("Home") {
                withAnimation(.default) {
                    router.currentPage = .HomePage                    
                }
            })
        }
    }
    
    func signOut() {
        let firebaseAuth = Auth.auth()
        do {
            try firebaseAuth.signOut()
            router.currentPage = .SignInPage
        } catch let signOutError as NSError {
            print("Error signing out: %@", signOutError)
        }
    }
}


struct SettingView_Previews: PreviewProvider {
    static var previews: some View {
        SettingView(router: Router())
    }
}
