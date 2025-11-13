import React from 'react';
import { View, StyleSheet } from 'react-native';

const store = createStore(state);
console.log(store.getState());


const todos = {
  todos: [{
    text: 'Eat food',
    completed: true
  }, {
    text: 'Exercise',
    completed: false
  }],
  visibilityFilter: 'SHOW_COMPLETED'
}


store.dispatch({
  type: 'COMPLETE_TODO',
  index: 1
});
store.dispatch({
  type: 'SET_VISIBILITY_FILTER',
  filter: 'SHOW_COMPLETED'
});


export default todos;