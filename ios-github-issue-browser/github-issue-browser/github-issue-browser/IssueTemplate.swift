//
//  IssueTemplate.swift
//  github-issue-browser
//
//  useful resouce:
//      json handling: https://matteomanferdini.com/codable/
//
//  Created by Lor Worwag on 3/8/21.
//

import Foundation

struct IssueTemplate: Codable, Identifiable {
    let url: String?
    var comments_url: String?
    var id: Int
    var number: Int?
    var title: String?
    var user: UserTemplate?
    var state: String?
    var locked: Bool
    var comments: Int?
    var created_at: String?
    var updated_at: String?
    var closed_at: String?
    var body: String?
}

struct UserTemplate: Codable, Identifiable {
    var login: String
    var id: Int
}

struct LabelTemplate: Codable, Identifiable {
    var id: Int
    var name: String
}

struct CommentTemplate: Codable, Identifiable {
    var url: String?
    var issue_url: String?
    var id: Int
    var user: UserTemplate?
    var created_at: String?
    var body: String?
}
