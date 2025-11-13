import React from 'react';
import { View, Text, Button } from 'react-native';
import { useSelector, useDispatch } from 'react-redux';
import { buyCake } from '../redux';

function HooksCakeContainer() {
  const numOfCakes = useSelector(state => state.cake.numOfCakes);
  const dispatch = useDispatch();

  return (
    <View>
      <Text>Number of cakes - {numOfCakes}</Text>
      <Button title='Buy Cake' onPress={() => dispatch(buyCake())} />
    </View>
  );
}

export default HooksCakeContainer;