import React, { useState } from 'react';
import { View, TextInput, Button, StyleSheet, Modal } from 'react-native';

const GoalInput = props => {
  const [enteredGoal, setEnteredGoal] = useState('');

  const goalInputHandler = (enteredGoal) => {
    setEnteredGoal(enteredGoal);
  };

  const addGoalHandler = () => {
    props.onAddGoal(enteredGoal);
    setEnteredGoal('');
  };

  return(
    <Modal visible={props.visible} animationType='slide'>
      <View style={styles.inputContainer}>

        <TextInput 
          placeholder='Course Goal' 
          style={styles.input} 
          onChangeText={goalInputHandler} 
        />
      <View style={styles.buttonContainer}>
        <View style={styles.button}>
          <Button 
            title="ADD" 
            onPress={addGoalHandler}
          />
        </View>
        <View style={styles.button}>
          <Button 
            title="CANCLE" 
            color='red'
            onPress={props.onCancel}
          />
        </View>
      </View>
    </View>
  </Modal>
  );
};

const styles = StyleSheet.create({
  inputContainer: {
    flex: 1,
    justifyContent: 'center', 
    alignItems: 'center',
    padding: 50,
  },
  input: {
    alignItems: 'center',
    width: '80%',
    borderColor: 'black',
    borderWidth: 1, 
    padding: 10,
    marginBottom: 10
  },
  buttonContainer: {
    flexDirection: 'row',
    justifyContent: 'space-around',
    alignItems: 'center',
    width: '80%',
  },
  button: {
    width: '40%',
  },
});

export default GoalInput; 