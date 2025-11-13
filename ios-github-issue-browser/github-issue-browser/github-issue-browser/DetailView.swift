//
//  DetailView.swift
//  github-issue-browser
//
//  Created by Lor Worwag on 3/8/21.
//

import SwiftUI

struct DetailView: View {
    
    @ObservedObject var githubIssueBrowserVM: GithubIssueBrowserVM
    @State var issue: IssueTemplate
    
    var body: some View {
        ScrollView {
            VStack(alignment: .leading) {
                HStack {
                    Spacer()
                    Text("Title")
                        .font(.title)
                    Spacer()
                }
                Text(issue.title!)
                    .font(.headline)
                    .padding(5)
                Divider()
                
                HStack {
                    Spacer()
                    Text(issue.state!)
                        .padding(5)
                    Text("#\(issue.number!)")
                        .padding(5)
                    Text(issue.created_at!)
                    Spacer()
                }.foregroundColor(.gray)
                Divider()
                
                HStack {
                    Spacer()
                    Text("Description")
                        .font(.title)
                        .padding(5)
                    Spacer()
                }
                Text(issue.body!)
                    .padding(5)
                Divider()
                
                HStack {
                    Spacer()
                    Text("Comments")
                        .font(.title)
                        .padding(5)
                    Spacer()
                }
                if githubIssueBrowserVM.comments.count > 0 {
                    ForEach(githubIssueBrowserVM.comments) { comment in
                        HStack {
                            Text("Username: ")
                                .padding(5)
                            Text(comment.user!.login)
                        }
                        Text(comment.body!)
                            .padding(5)
                            .padding(.bottom, 5)
                    }
                }
                
            }
            
        }
    }
    
}













//struct DetailView_Previews: PreviewProvider {
//    static var previews: some View {
//        DetailView()
//    }
//}
