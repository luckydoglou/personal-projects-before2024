//
//  ContentViewModel.swift
//  InstagramMock
//
//  Created by Lor Worwag on 8/31/24.
//

import Foundation
import FirebaseAuth
import Combine

class ContentViewModel: ObservableObject {
    private let service = AuthService.shared
    private var cancellables = Set<AnyCancellable>()
    @Published var userSession: FirebaseAuth.User?
    @Published var currentUser: User?
    
    init() {
        setupSubscriber()
    }
    
    func setupSubscriber() {
        service.$userSession.sink { [weak self] userSession in
            self?.userSession = userSession
        }
        .store(in: &cancellables) 
        
        service.$currentUser.sink { [weak self] currentUser in
            self?.currentUser = currentUser
        }
        .store(in: &cancellables)
    }
}
