/*
 * Copyright 2021 Lor Worwag,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Purpose: This file is used as a router to change between different views
 * based on a publisher's value.
 *
 * This app includes Sign-In, Sign-Up functionalities. It can scan food
 * products' barcodes and display relative barcode data. Data is communicated
 * through Firebase Real-Time Database.
 *
 * @author Lor Worwag lor.worwag@gmail.com
 *
 * @version Mar, 2021
 */

import SwiftUI

struct RouterView: View {
    @StateObject var router: Router

    var body: some View {
        switch router.currentPage {
        case .SignInPage:
            SignInView(router: router)
        case .RegisterPage:
            RegisterView(router: router)
        case .HomePage:
            HomeView(router: router)
        case .SettingPage:
            SettingView(router: router)
        }
    }
}

// MARK:- View Models

class Router: ObservableObject {
    @Published var currentPage: Page = .SignInPage
}

// MARK:- Templates

enum Page {
    case SignInPage
    case RegisterPage
    case HomePage
    case SettingPage
}
