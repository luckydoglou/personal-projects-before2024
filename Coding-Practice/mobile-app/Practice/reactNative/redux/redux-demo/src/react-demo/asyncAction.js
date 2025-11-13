const redux = require('redux');
const thunk = require('redux-thunk').default;
const axios = require('axios');
const createStore = redux.createStore;
const applyMiddleware = redux.applyMiddleware;

// initial state
const initialState = {
  loading: false,
  users: [],
  error: "",
}

// actions
const FETCH_USERS_REQUEST = 'FETCH_USERS_REQUEST';
const FETCH_USERS_SUCCESS = 'FETCH_USERS_SUCCESS';
const FETCH_USERS_FAILURE = 'FETCH_USERS_FAILURE';

// action creators
const fetchUserRequest = () => {
  return {
    type: FETCH_USERS_REQUEST,
  }
}

const fetchUserSuccess = users => {
  return {
    type: FETCH_USERS_SUCCESS,
    payload: users
  }
}

const fetchUserFailure = error => {
  return {
    type: FETCH_USERS_FAILURE,
    payload: error,
  }
}

const fetchUsers = () => {
  return dispatch => {
    dispatch(fetchUserRequest());
    axios.get('https://jsonplacehlder.typicode.com/users')
      .then(res => {
        // res.data is the array of users
        const users = res.data.map(users => users.id);
        dispatch(fetchUserSuccess(users));
      })
      .catch(error => {
        // error.message
        dispatch(fetchUserFailure(error.message));
      })
  }
}

// reducers
const reducer = (state = initialState, action) => {
  switch(action.type) {
    case FETCH_USERS_REQUEST:
      return {
        ...state,
        loading: true,
      }
    case FETCH_USERS_SUCCESS:
      return {
        loading: false,
        users: action.payload,
        error: "",
      }
    case FETCH_USERS_FAILURE:
      return {
        loading: false,
        users: [],
        error: action.payload,
      }
  }
}

// store
const store = createStore(reducer, applyMiddleware(thunk));
const unsubscribe = store.subscribe(() => console.log(store.getState()));
store.dispatch(fetchUsers());
