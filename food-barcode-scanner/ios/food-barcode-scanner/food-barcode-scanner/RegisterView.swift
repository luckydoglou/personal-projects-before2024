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
 * Purpose: This file loads Sign-Up screen and register users base on the
 * email and password they provide.
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

struct RegisterView: View {
    
    @StateObject var router: Router
    @State var email: String = ""
    @State var password: String = ""
    @State var showAlert = false
    @State var registerFailedAlert = false
    
    var body: some View {
        VStack {
            Text("Create Account")
                .font(.title)
            
            TextField("Email", text: $email)
                .autocapitalization(.none)
                .disableAutocorrection(true)
                .frame(width: 150, height: 30, alignment: .center)
                .padding(.top, 20)
                .padding(.horizontal, 20)
            SecureField("Password", text: $password)
                .autocapitalization(.none)
                .disableAutocorrection(true)
                .frame(width: 150, height: 30, alignment: .center)
                .padding(.horizontal, 20)
            
            Button(action: {
                Register()
            }, label: { Text("Register") })
                .padding(.top, 20)
                .alert(isPresented: $registerFailedAlert) {
                    Alert(title: Text("Register Failed"), message: Text("Could Not Register with Entered Email and Password"))
                }
            Button(action: { router.currentPage = .SignInPage }, label: { Text("Already Have an Account? Sign In") })
                .padding()
        }
    }
    
    func Register() {
        Auth.auth().createUser(withEmail: email, password: password) { (authDataResult, error) in
            if error != nil {
                registerFailedAlert = true
                print(error?.localizedDescription ?? "")
            } else {
                router.currentPage = .SignInPage
                print("Sign Up Success")
            }
        }
    }
    
}


struct RegisterView_Previews: PreviewProvider {
    static var previews: some View {
        RegisterView(router: Router())
    }
}
