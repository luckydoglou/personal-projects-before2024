//
//  LoginViewModel.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/31/24.
//

import Foundation

class LoginViewModel: ObservableObject {
    @Published var email = ""
    @Published var password = ""
    
    func signIn() async throws {
        try await AuthService.shared.login(withEmail: email, password: password)
    }
}
