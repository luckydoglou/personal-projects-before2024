import React, {useEffect} from 'react';
import { View, Text, StyleSheet } from 'react-native';
import {fetchUsers, fetchUserFailure} from '../redux';
import {connect} from 'react-redux';

function UserContainer({ userData, fetchUsers }) {
  useEffect(() => {
    fetchUsers()
  }, [])
  
  return userData.loading ? (
    <Text>Loading</Text>
  ) : userData.error ? (
    <Text>{userData.error}</Text>
  ) : (
    <View>
      <Text>Users List</Text>
      <View>
        {userData &&
          userData.users &&
          userData.users.map(user => <Text>{user.name}</Text>)}
      </View>
    </View>
  )
}

const mapStateToProps = state => {
  return {
    userData: state.user
  }
}

const mapDispatchToProps = dispatch => {
  return {
    fetchUsers: () => dispatch(fetchUsers())
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(UserContainer);