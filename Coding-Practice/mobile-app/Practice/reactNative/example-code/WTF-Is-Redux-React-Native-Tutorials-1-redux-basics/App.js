import React from "react";
import {
    View,
    Text,
    StyleSheet,
    TouchableOpacity
} from "react-native";
import { createStore } from 'redux'
import CounterApp from './src/CounterApp'
import { Provider } from 'react-redux'

const initState = {
    counter: 0
};

const reducer = (state = initState, action) => {
    switch (action.type) {
        case 'INCREASE_COUNTER':
            return ({counter: state.counter + 1});
        case 'DECREASE_COUNTER':
            return ({counter: state.counter - 1});
    }
    return state;
};

const store = createStore(reducer);

function App() {
    return (
        <Provider store={store}>
            <CounterApp />
        </Provider>
    );
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        alignItems: 'center',
        justifyContent: 'center'
    }
});

export default App