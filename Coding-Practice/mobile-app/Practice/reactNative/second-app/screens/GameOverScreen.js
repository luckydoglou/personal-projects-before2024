import React from 'react';
import {View, Text, StyleSheet, Button} from 'react-native';

const GameOverScreen = props => {
  return (
    <View style={styles.screen}>
      <Text style={styles.gameOverTitle}>The Game is Over!</Text>
      <Text style={styles.textBody}>Number of rounds: {props.roundsNumber}</Text>
      <Text style={styles.textBody}>Number was: {props.userNumber}</Text>
      <Button title="NEW GAME" onPress={props.onRestart} />
    </View>
  );
};

const styles = StyleSheet.create({
  screen: {
    flexDirection: 'column',
    justifyContent: 'center',
    alignItems: 'center',
  },
  gameOverTitle: {
    fontSize: 22,
    padding: 20,
    paddingTop: 50,
  },
  textBody: {
    paddingBottom: 20,
  }
});

export default GameOverScreen;