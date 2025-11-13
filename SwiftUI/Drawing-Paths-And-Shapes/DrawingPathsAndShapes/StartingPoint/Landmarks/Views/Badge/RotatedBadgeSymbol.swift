//
//  RotatedBadgeSymbol.swift
//  Landmarks
//
//  Created by Lor Worwag on 1/21/24.
//  Copyright © 2024 Apple. All rights reserved.
//

import SwiftUI

struct RotatedBadgeSymbol: View {
    let angle: Angle
        
    var body: some View {
        BadgeSymbol()
            .padding(-60)
            .rotationEffect(angle, anchor: .bottom)
    }
}

#Preview {
    RotatedBadgeSymbol(angle: Angle(degrees: 5))
}
