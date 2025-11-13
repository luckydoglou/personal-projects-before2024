// import {createStore} from 'redux';
const redux = require('redux');
const reduxLogger = require('redux-logger');
const createStore = redux.createStore;
const combineReducers = redux.combineReducers;
const applyMiddleware = redux.applyMiddleware;
const logger = reduxLogger.createLogger();

// action type
const BUY_CAKE = 'BUY_CAKE';
const BUY_ICECREAM = 'BUY_ICECREAM';

// action function
// action({})
const buy_cake = () => {
  return {
    type: BUY_CAKE,
    info: 'First redux action',
  }
}

const buy_icecream = () => {
  return {
    type: BUY_ICECREAM,
  }
}

// reducer
// (previousState, action) => newState
// state = {}
const initialCakeState = {
  numOfCakes: 10,
}
const initialIcecreamState = {
  numOfIcecreams: 20,
}

const cakeReducer = (state = initialCakeState, action) => {
  switch(action.type) {
    case BUY_CAKE:
      return {
        ...state,
        numOfCakes: state.numOfCakes - 1,
      }
    default:
      return state;
  }
}
const icecreamReducer = (state = initialIcecreamState, action) => {
  switch(action.type) {
    case BUY_ICECREAM:
      return {
        ...state,
        numOfIcecreams: state.numOfIcecreams - 1,
      }
    default:
      return state;
  }
}

const rootReducer = combineReducers({
  cake: cakeReducer,
  icecream: icecreamReducer,
});

// store
const store = createStore(rootReducer, applyMiddleware(logger));
console.log("Initial state: ", store.getState());
// subscribe(())
// const unsubscribe = store.subscribe(() => console.log("Updated state: ", store.getState()));
unsubscribe = store.subscribe(() => {});
// dispatch(action/action())
store.dispatch(buy_cake());
store.dispatch(buy_cake());
store.dispatch({type: BUY_CAKE});
store.dispatch(buy_icecream());
store.dispatch(buy_icecream());

unsubscribe();
