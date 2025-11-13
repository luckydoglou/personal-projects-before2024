import React from 'react';
import { View, Text, StyleSheet, Button } from 'react-native';
import {connect} from 'react-redux';
import {buyCake, buyIceCream} from '../redux';

function ItemContainer(props) {
  return (
    <View>
      <Text>Item - {props.item}</Text>
      <Button title='Buy Items' onPress={props.buyItem} />
    </View>
  );
}

const mapStateToProps = (state, ownProps) => {
  const itemState = ownProps.cake ? state.cake.numOfCakes : state.iceCream.numOfIceCreams;

  return {
    item: itemState
  }
}

const mapDispatchToProps = (dispatch, ownProps) => {
  const dispatchFunction = ownProps.cake ? () => dispatch(buyCake()) : () => dispatch(buyIceCream());

  return {
    buyItem: dispatchFunction,
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(ItemContainer);