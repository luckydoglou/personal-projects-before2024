//
//  Post.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/30/24.
//

import Foundation
import Firebase

struct Post: Identifiable, Hashable, Codable {
    let id: String
    let ownerUid: String
    let caption: String
    var likes: Int
    let imageUrl: String
    let timestamp: Timestamp
    var user: User?
}

extension Post {
    static var MOCK_POSTS: [Post] = [
        .init(id: NSUUID().uuidString, 
              ownerUid: NSUUID().uuidString,
              caption: "Batman is here, tremble!",
              likes: 123,
              imageUrl: "Batman",
              timestamp: Timestamp(),
              user: User.MOCK_USERS[0]),
        .init(id: NSUUID().uuidString, 
              ownerUid: NSUUID().uuidString,
              caption: "Venom wants you bad, yum yum!",
              likes: 124, imageUrl: "Venom",
              timestamp: Timestamp(),
              user: User.MOCK_USERS[1]),
        .init(id: NSUUID().uuidString,
              ownerUid: NSUUID().uuidString,
              caption: "Wakanda Forever!",
              likes: 125,
              imageUrl: "Black-Panther-1",
              timestamp: Timestamp(),
              user: User.MOCK_USERS[2]),
        .init(id: NSUUID().uuidString,
              ownerUid: NSUUID().uuidString,
              caption: "Wakanda Forever Forever!",
              likes: 126,
              imageUrl: "Black-Panther-1",
              timestamp: Timestamp(),
              user: User.MOCK_USERS[2])
    ]
}
