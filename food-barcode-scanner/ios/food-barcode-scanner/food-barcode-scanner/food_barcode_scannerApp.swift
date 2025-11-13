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
 * Purpose: This file initiate the app.
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
import Firebase

@main
struct food_barcode_scannerApp: App {
    @StateObject var router: Router = Router()
    
    init() {
        // Use Firebase library to configure APIs
        FirebaseApp.configure()
    }
    
    var body: some Scene {
        WindowGroup {
            RouterView(router: router)
        }
    }
}

