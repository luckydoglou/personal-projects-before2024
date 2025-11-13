import { createStore } from 'redux';
import { Provider } from 'react-redux';
import rootReducer from './reducers/rootReducer';
import {connect} from 'react-redux';

const store = createStre(rootReducer);

ReactDom.render(<Provider store={store}><App /></Provider>);

const mapStateToProps = (state) => {

}

export default connect(mapStateToProps)(App);