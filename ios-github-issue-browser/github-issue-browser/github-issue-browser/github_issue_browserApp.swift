//
//  github_issue_browserApp.swift
//  github-issue-browser
//
//  Created by Lor Worwag on 3/8/21.
//

import SwiftUI

@main
struct github_issue_browserApp: App {
    
    let githubIssueBrowserVM: GithubIssueBrowserVM
    
    init() {
        githubIssueBrowserVM = GithubIssueBrowserVM()
    }
    
    var body: some Scene {
        WindowGroup {
            ContentView(githubIssueBroswerVM: githubIssueBrowserVM)
        }
    }
    
}
