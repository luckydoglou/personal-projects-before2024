import React from 'react';
import { View, Text, StyleSheet, Button } from 'react-native';
import { connect } from 'react-redux';
import { buyCake } from '../redux';

function CakeContainer(props) {
  return (
    <View>
      <Text>Number of cakes - {props.numOfCakes}</Text>
      <Button title='Buy Cake' onPress={props.buyCake} />
    </View>
  );
}

const mapStateToProps = state => {
  return {
    numOfCakes: state.cake.numOfCakes,
  }
}

const mapDispatchToProps = dispatch => {
  return {
    buyCake: () => dispatch(buyCake())
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(CakeContainer);