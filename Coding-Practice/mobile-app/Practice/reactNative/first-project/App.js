// import React, { Component } from 'react';
// import { Image, ScrollView, Platform, TouchableHighlight, TouchableOpacity, 
//   TouchableNativeFeedback, TouchableWithoutFeedback, 
//   StyleSheet, Text, TextInput, View, Button } from 'react-native';

// export default class AlignItemsBasics extends Component {
//   constructor(props) {
//     super(props);
//     this.state = {text: ''};
//   }

//   onPressButton() {
//     alert('You tapped the button')
//   }

//   onLongPressButton() {
//     alert('You long-pressed the button')
//   }

//   render() {
//     return(
//       <ScrollView>
//         <View style={styles.container}>
//           <TextInput 
//             style={{height: 100}}
//             placeholder="Type here to translate!"
//             onChangeText={(text) => this.setState({text})}
//             value={this.state.text}
//           ></TextInput>
//           <Text style={{padding: 10, fontSize: 42}}>
//             {this.state.text.split(' ').map((word) => word && '🍕').join(' ')}
//           </Text>

//           <View style={styles.buttonContainer}>
//             <Button
//               onPress={this.onPressButton}
//               title="Press Me"
//               color='blue'
//             />
//           </View>

//           <View style={styles.altLayout}>
//             <Button
//               onPress={this.onPressButton}
//               title='OK!'
//               color='red'
//             />
//           </View>

//           <TouchableOpacity onPress={this.onPressButton}>
//             <View style={styles.button}>
//               <Text style={{color: 'white', alignItems: 'center'}}>
//                 TouchableOpacity
//               </Text>
//             </View>
//           </TouchableOpacity>

//           <TouchableHighlight
//             onPress={this.onPressButton}
//             onLongPress={this.onLongPressButton}
//             underlayColor='white'>
//               <View style={styles.button}>
//                 <Text style={{color: 'white'}}>
//                   Touchable with Long Press
//                 </Text>
//               </View>
//             </TouchableHighlight>

//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />
//           <Image source={{uri: "https://facebook.github.io/react-native/img/tiny_logo.png", width: 64, height: 64}} />

//         </View>
//       </ScrollView>
//     );
//   }
// };

// const styles = StyleSheet.create({
//   container: {
//     flex: 1,
//     justifyContent: 'center'
//   },
//   buttonContainer: {
//     margin: 20
//   },
//   altLayout: {
//     margin: 20,
//     flexDirection: 'row',
//     justifyContent: 'space-between'
//   },
//   button: {
//     marginBottom: 30,
//     width: 260,
//     alignItems: 'center',
//     backgroundColor: 'blue'
//   }
// });

import React from 'react';
import { FlatList, ActivityIndicator, Text, View  } from 'react-native';

export default class FetchExample extends React.Component {

  constructor(props){
    super(props);
    this.state ={ isLoading: true}
  }

  componentDidMount(){
    return fetch('https://facebook.github.io/react-native/movies.json')
      .then((response) => response.json())
      .then((responseJson) => {

        this.setState({
          isLoading: false,
          dataSource: responseJson.movies,
        }, function(){

        });

      })
      .catch((error) =>{
        console.error(error);
      });
  }



  render(){

    if(this.state.isLoading){
      return(
        <View style={{flex: 1, padding: 20}}>
          <ActivityIndicator/>
        </View>
      )
    }

    return(
      <View style={{flex: 1, paddingTop:20}}>
        <FlatList
          data={this.state.dataSource}
          renderItem={({item}) => <Text>{item.title}, {item.releaseYear}</Text>}
          keyExtractor={({id}, index) => id}
        />
      </View>
    );
  }
}