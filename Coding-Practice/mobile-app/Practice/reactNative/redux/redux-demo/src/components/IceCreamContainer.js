import React from 'react';
import { View, Text, StyleSheet, Button } from 'react-native';
import { connect } from 'react-redux';
import { buyIceCream } from '../redux';

function IceCreamContainer(props) {
  return (
    <View>
      <Text>Number of cakes - {props.numOfIceCreams}</Text>
      <Button title='Buy Ice Cream' onPress={props.buyIceCream} />
    </View>
  );
}

const mapStateToProps = state => {
  return {
    numOfIceCreams: state.iceCream.numOfIceCreams,
  }
}

const mapDispatchToProps = dispatch => {
  return {
    buyIceCream: () => dispatch(buyIceCream())
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(IceCreamContainer);