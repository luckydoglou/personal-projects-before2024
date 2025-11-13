import React, {useState} from 'react';
import { View, Text, StyleSheet, Button, TextInput } from 'react-native';
import { connect } from 'react-redux';
import { buyCake } from '../redux';

function NewCakeContainer(props) {
  const [number, setNumber] = useState(1);

  return (
    <View>
      <Text>Number of cakes - {props.numOfCakes}</Text>
      <TextInput style={styles.input} onChangeText={num => setNumber(num)} value={number} />
      <Button title='Buy Cake' onPress={() => props.buyCake(number)} />
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
    buyCake: number => dispatch(buyCake(number))
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(NewCakeContainer);

const styles = StyleSheet.create({
  input: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1
  }
});