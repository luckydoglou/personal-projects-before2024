/**
 * Youtube Link: https://www.youtube.com/watch?v=7CqJlxBYj-M
 * Github repo: https://github.com/beaucarnes/mern-exercise-tracker-mongodb
 * 
 */
import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import * as serviceWorker from './serviceWorker';

ReactDOM.render(<App />, document.getElementById('root'));

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister();
