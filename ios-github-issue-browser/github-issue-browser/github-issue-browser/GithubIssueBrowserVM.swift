//
//  GithubIssueBrowserVM.swift
//  github-issue-browser
//
//  useful resouce:
//      json handling: https://matteomanferdini.com/codable/
//
//  Created by Lor Worwag on 3/8/21.
//

import Foundation
import SwiftUI

class GithubIssueBrowserVM: ObservableObject {
    
    @Published var issues: Array<IssueTemplate> = []
    @Published var comments: Array<CommentTemplate> = []
    
    init() {
        fetchData()
    }
    
    func fetchData() {
        let url = URL(string: "https://api.github.com/repos/walmartlabs/thorax/issues")!
        
        URLSession.shared.dataTask(with: url) { (data, response, error) in
            if let error = error {
                print("Error took place \(error)")
                return
            }
            if let response = response as? HTTPURLResponse {
                print("Response HTTP status code: \(response.statusCode)")
            }
            DispatchQueue.main.async {
                if let data = data {
                    let i = try? JSONDecoder().decode([IssueTemplate].self, from: data)
                    self.issues = i!
                }
            }
        }.resume()
    }
  
    func fetchComments(urlString: String) {
        comments = []
        let url = URL(string: urlString)!

        URLSession.shared.dataTask(with: url) { (data, response, error) in
            if let error = error {
                print("Error took place \(error)")
                return
            }
            if let response = response as? HTTPURLResponse {
                print("Response HTTP status code: \(response.statusCode)")
            }
            DispatchQueue.main.async {
                if let data = data {
                    let i = try? JSONDecoder().decode([CommentTemplate].self, from: data)
                    self.comments = i!
                }
            }
        }.resume()
    }
    
}
