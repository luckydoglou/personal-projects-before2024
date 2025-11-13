//
//  UserStatsView.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/27/24.
//

import SwiftUI

struct UserStatsView: View {
    let value: Int
    let title: String
    var body: some View {
        VStack {
            Text("\(value)")
                .font(.subheadline)
                .fontWeight(.semibold)
            Text(title)
                .font(.footnote)
        }
        .frame(width: 76)
    }
}

#Preview {
    UserStatsView(value: 12, title: "Posts")
}
