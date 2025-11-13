//
//  ProfileView.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/26/24.
//

import SwiftUI

struct ProfileView: View {
    let user: User
    
    var body: some View {
        ScrollView {
            ProfileHeaderView(user: user)
            PostGridView(user: user)
        }
        .navigationTitle("Profile")
        .navigationBarTitleDisplayMode(.inline)
    }
}

#Preview {
    ProfileView(user: User.MOCK_USERS[2])
}
