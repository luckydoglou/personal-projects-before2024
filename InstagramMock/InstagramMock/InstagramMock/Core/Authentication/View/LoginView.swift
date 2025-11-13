//
//  LoginView.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/30/24.
//

import SwiftUI

struct LoginView: View {
    @StateObject var viewModel = LoginViewModel()
    
    var body: some View {
        NavigationStack {
            VStack {
                Spacer()
                // logo image
                Image("instagram-logo")
                    .resizable()
                    .scaledToFit()
                    .frame(width: 220, height: 100)
                // text fields
                VStack {
                    TextField("Enter your email", text: $viewModel.email)
                        .autocapitalization(.none)
                        .modifier(IGTextFieldModifier())
                    SecureField("Enter your password", text: $viewModel.password)
                        .modifier(IGTextFieldModifier())
                }
                Button {
                    print("Forget password button clicked")
                } label: {
                    Text("Forget Password?")
                        .font(.footnote)
                        .fontWeight(.semibold)
                        .padding(.top)
                        .padding(.trailing, 28)
                }
                .frame(maxWidth: .infinity, alignment: .trailing)
                Button {
                    Task { try await viewModel.signIn() }
                } label: {
                    Text("Login")
                        .font(.subheadline)
                        .fontWeight(.semibold)
                        .foregroundStyle(.white)
                        .frame(width: 360, height: 44)
                        .background(Color(.systemBlue))
                        .clipShape(.rect(cornerRadius: 8))
                }
                // divider
                LabelledDividerView(label: "OR")
                // 3rd party login
                Button {
                    print("Continue with Facebook button clicked")
                } label: {
                    Image("facebook-logo")
                        .resizable()
                        .scaledToFit()
                        .frame(width: 15, height: 15)
                    Text("Continue with Facebook")
                        .font(.subheadline)
                        .fontWeight(.semibold)
                }
                Spacer()
                Divider()
                NavigationLink {
                    AddEmailView()
                        .navigationBarBackButtonHidden(true)
                } label: {
                    HStack(spacing: 4) {
                        Text("Don't have an account?")
                        Text("Sign Up")
                            .fontWeight(.semibold)
                    }
                    .font(.footnote)
                }
                .padding(.vertical, 16)

            }
        }
    }
}

#Preview {
    LoginView()
}
