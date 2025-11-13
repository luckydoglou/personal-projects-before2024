//
//  IGTextFieldModifier.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/30/24.
//

import SwiftUI

struct IGTextFieldModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .font(.subheadline)
            .padding(12)
            .background(Color(.systemGray6))
            .clipShape(.rect(cornerRadius: 10))
            .padding(.horizontal, 24)
    }
}
