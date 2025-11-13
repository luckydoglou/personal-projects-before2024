//
//  LandmarkList.swift
//  Landmarks
//
//  Created by Lor Worwag on 1/14/24.
//  Copyright © 2024 Apple. All rights reserved.
//

import SwiftUI

struct LandmarkList: View {
    var body: some View {
        NavigationSplitView {
            List(landmarks) { landmark in
                NavigationLink {
                    LandmarkDetail(landmark: landmark)
                } label: {
                    LandmarkRow(landmark: landmark)
                }
            }
            .navigationTitle("Landmarks")
        } detail: {
            Text("Select a landmark")
        }

        
    }
}

#Preview {
    LandmarkList()
}
