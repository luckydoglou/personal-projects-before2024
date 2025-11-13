//
//  User.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/30/24.
//

import Foundation
import FirebaseAuth

struct User: Identifiable, Hashable, Codable {
    let id: String
    var username: String
    var profileImageUrl: String?
    var fullname: String?
    var bio: String?
    let email: String
    
    var isCurrentUser: Bool {
        guard let currentUid = Auth.auth().currentUser?.uid else { return false }
        return currentUid == id
    }
}

extension User {
    static var MOCK_USERS: [User] = [
        .init(id: NSUUID().uuidString, 
              username: "batman",
              profileImageUrl: nil,
              fullname: "Bruce Wayne",
              bio: "Gothem's dark knight",
              email: "batman@gmail.com"),
        .init(id: NSUUID().uuidString, 
              username: "venom",
              profileImageUrl: nil,
              fullname: "Eddie Brock",
              bio: "Venom", 
              email: "venom@gmail.com"),
        .init(id: NSUUID().uuidString,
              username: "blackpanther",
              profileImageUrl: nil,
              fullname: "T'Challa",
              bio: "Wakanda Forever ", 
              email: "blackpather@gmail.com"),
    ]
}
