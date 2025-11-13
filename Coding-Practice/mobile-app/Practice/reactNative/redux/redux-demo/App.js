/**
 * Youtube Link: https://www.youtube.com/playlist?list=PLC3y8-rFHvwheJHvseC3I0HuYI2f46oAK
 */
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
import {Provider} from 'react-redux';

import store from './src/redux/store';
import CakeContainer from './src/components/CakeContainer';
import HooksCakeContainer from './src/components/HooksCakeContainer';
import IceCreamContainer from './src/components/IceCreamContainer';
import NewCakeContainer from './src/components/NewCakeContainer';
import ItemContainer from './src/components/ItemContainer';
import UserContainer from './src/components/UserContainer';

export default function App() {
  return (
    <Provider store={store}>
      <View style={styles.container}>
        <UserContainer />
        {/* <ItemContainer cake />
        <ItemContainer />
        <CakeContainer />
        <HooksCakeContainer />
        <IceCreamContainer />
        <NewCakeContainer /> */}
      </View>
    </Provider>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
