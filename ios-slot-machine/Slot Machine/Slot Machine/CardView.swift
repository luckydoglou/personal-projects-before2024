//
//  CardView.swift
//  Slot Machine
//
//  Created by Lor Worwag on 1/15/21.
//

import SwiftUI

struct CardView: View {
    @Binding var symbol: String
    @Binding var backgroundColor: Color
    
    var body: some View {
        
        Image(symbol)
            .resizable()
            .aspectRatio(1, contentMode: .fit)
            .background(backgroundColor.opacity(0.5))
            .cornerRadius(30.0)
        
    }
}

struct CardView_Previews: PreviewProvider {
    static var previews: some View {
        CardView(symbol: Binding.constant("cherry"), backgroundColor: Binding.constant(Color.white))
    }
}
