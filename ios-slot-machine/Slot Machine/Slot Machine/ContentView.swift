//
//  ContentView.swift
//  Slot Machine
//
//  Created by Lor Worwag on 1/14/21.
//

import SwiftUI

struct ContentView: View {
    @State private var symbols = ["apple", "star", "cherry"]
    @State private var numbers = Array(repeating: 0, count: 9)
    @State private var backgroundColors = Array(repeating: Color.white, count: 9)
    @State private var credits = 1000
    @State private var betAmount = 5
    
    var body: some View {
        
        ZStack {
            // background
            Rectangle()
                .foregroundColor(Color(red: 200/255, green: 143/255, blue: 32/255))
                .ignoresSafeArea(.all)
            Rectangle()
                .foregroundColor(Color(red: 228/255, green: 195/255, blue: 76/255))
                .rotationEffect(Angle(degrees: 45.0))
                .ignoresSafeArea(.all)
            
            // foreground contents
            VStack {
                Spacer()
                
                // title
                HStack {
                    Image(systemName: "star.fill")
                        .foregroundColor(.yellow)
                    Text("Jackpot!")
                        .foregroundColor(.white)
                        .fontWeight(.bold)
                    Image(systemName: "star.fill")
                        .foregroundColor(.yellow)
                }
                    .scaleEffect(2)
                Spacer()
                
                // 'credits' counter
                Text("Credits: \(credits)")
                    .padding()
                    .background(Color.white.opacity(0.5))
                    .cornerRadius(20.0)
                Spacer()
                
                // cards
                VStack {
                    HStack {
                        Spacer()
                        CardView(symbol: $symbols[numbers[0]], backgroundColor: $backgroundColors[0])
                        CardView(symbol: $symbols[numbers[1]], backgroundColor: $backgroundColors[1])
                        CardView(symbol: $symbols[numbers[2]], backgroundColor: $backgroundColors[2])
                        Spacer()
                    }
                    HStack {
                        Spacer()
                        CardView(symbol: $symbols[numbers[3]], backgroundColor: $backgroundColors[3])
                        CardView(symbol: $symbols[numbers[4]], backgroundColor: $backgroundColors[4])
                        CardView(symbol: $symbols[numbers[5]], backgroundColor: $backgroundColors[5])
                        Spacer()
                    }
                    HStack {
                        Spacer()
                        CardView(symbol: $symbols[numbers[6]], backgroundColor: $backgroundColors[6])
                        CardView(symbol: $symbols[numbers[7]], backgroundColor: $backgroundColors[7])
                        CardView(symbol: $symbols[numbers[8]], backgroundColor: $backgroundColors[8])
                        Spacer()
                    }
                }
                Spacer()
                
                // buttons
                HStack(spacing: 20) {
                    VStack {
                        // 'spin' button
                        Button(action: {
                            processResults()
                            
                        }, label: {
                            Text("Spin")
                                .fontWeight(.bold)
                                .padding()
                                .padding(.horizontal, 30)
                                .background(Color.red)
                                .foregroundColor(.white)
                                .cornerRadius(30.0)
                        })
                        Text("\(betAmount) credits")
                            .font(.footnote)
                            .padding(.top, 5)
                    }
                    
                    VStack {
                        // 'mega spin' button
                        Button(action: {
                            processResults(true)
                            
                        }, label: {
                            Text("Mega Spin")
                                .fontWeight(.bold)
                                .padding()
                                .padding(.horizontal, 30)
                                .background(Color.red)
                                .foregroundColor(.white)
                                .cornerRadius(30.0)
                        })
                        Text("\(betAmount * 5) credits")
                            .font(.footnote)
                            .padding(.top, 5)
                    }
                }

                Spacer()
            }
        }
    }
    
    func processResults(_ isMegaSpin: Bool = false) {
        backgroundColors = backgroundColors.map({ _ in
            Color.white
        })
        
        if !isMegaSpin {
            // normal spin
            numbers[3] = Int.random(in: 0...symbols.count - 1)
            numbers[4] = Int.random(in: 0...symbols.count - 1)
            numbers[5] = Int.random(in: 0...symbols.count - 1)
            
            processWin()
            
        } else {
            // mega spin
            numbers = numbers.map({ _ in
                Int.random(in: 0...symbols.count - 1)
            })
            
            processWin(true)
            
        }
        
    }
    
    func processWin(_ isMegaSpin: Bool = false) {
        var matches = 0
        
        if !isMegaSpin {
            if isMatch(3, 4, 5) { matches += 1 }
            
        } else {
            // check 3 rows and diagnals
            if isMatch(0, 1, 2) { matches += 1 }
            if isMatch(3, 4, 5) { matches += 1 }
            if isMatch(6, 7, 8) { matches += 1 }
            if isMatch(0, 4, 8) { matches += 1 }
            if isMatch(2, 4, 6) { matches += 1 }
        }
        
        // calculate the credits
        if !isMegaSpin {
            credits -= betAmount
        } else {
            credits -= betAmount * 5
        }
        credits += betAmount * matches * 2
    }
    
    func isMatch(_ index1: Int, _ index2: Int, _ index3: Int) -> Bool {
        if numbers[index1] == numbers[index2] && numbers[index2] == numbers[index3] {
            // change to winning background color
            backgroundColors[index1] = Color.green
            backgroundColors[index2] = Color.green
            backgroundColors[index3] = Color.green
            return true
        }
        return false
    }
    
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
