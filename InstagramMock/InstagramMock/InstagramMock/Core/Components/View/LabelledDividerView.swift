//
//  LabelledDividerView.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/30/24.
//

import SwiftUI

struct LabelledDividerView: View {

    let label: String
    let horizontalPadding: CGFloat
    let color: Color

    init(label: String, horizontalPadding: CGFloat = 20, color: Color = .gray) {
        self.label = label
        self.horizontalPadding = horizontalPadding
        self.color = color
    }

    var body: some View {
        HStack {
            line
            Text(label).foregroundColor(color)
            line
        }
    }

    var line: some View {
        VStack { Divider().background(color) }.padding(horizontalPadding)
    }
}

#Preview {
    LabelledDividerView(label: "OR")
}
