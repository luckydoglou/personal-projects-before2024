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
 * Purpose: This file loads the Sign-In screen and validates users base on
 * user's email and password.
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

struct SignInView: View {
    
    @StateObject var router: Router
    @State var email: String = ""
    @State var password: String = ""
    @State var userNotFoundAlert = false
    
    var body: some View {
            
        VStack {
            Text("Sign In")
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
            
            Button(action: { signIn() }, label: { Text("Sign In") })
                .padding(.top, 20)
                .alert(isPresented: $userNotFoundAlert) {
                    Alert(title: Text("User Not Found"), message: Text("Could Not Find User with Entered Email and Password"))
                }
            Button(action: { router.currentPage = .RegisterPage }, label: { Text("New User? Create an Account") })
                .padding()
        }
    }

    func signIn() {
        Auth.auth().signIn(withEmail: email, password: password) { (authDataResult, error) in
            if error != nil {
                print(error?.localizedDescription ?? "")
                userNotFoundAlert = true
            } else {
                router.currentPage = .HomePage
                print("Success")
            }
        }
    }
    
}


struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        SignInView(router: Router())
    }
}
