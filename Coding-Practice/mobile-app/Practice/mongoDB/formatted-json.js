// insert one
db.posts.insert({
  title: 'Post One',
  body: 'Body of post one',
  category: 'New',
  likes: 4,
  tags: ['news', 'events'],
  user: {
    name: 'John Doe',
    status: 'author'
  },
  date: Date()
})

// insert many
db.posts.insertMany([
  {
    title: 'Post Two',
    body: 'Body of post two',
    category: 'Technology',
    data: Date()
  },
  {
    title: 'Post Three',
    body: 'Body of post three',
    category: 'News',
    data: Date()
  },
  {
    title: 'Post Four',
    body: 'Body of post four',
    category: 'Entertainment',
    data: Date()
  },
])

// update
db.posts.update({ title: 'Post Two' },
  {
    title: 'Post Two',
    body: 'New post 2 body',
    date: Date()
  },
  {
    update: true
  }
)

db.posts.update({ title: 'Post Two' },
  {
    $set: {
      body: 'Body of post 2',
      category: 'Technology'
    }
  }
)

db.posts.update({ title: 'Post One' },
  {
    $set: {
      comments: [
        {
          user: 'Mary Williams',
          body: 'Comment One',
          date: Date()

        },
        {
          user: 'Henry White',
          body: 'Comment Two',
          date: Date()
        }
      ]
    }
  }
)

// find matched element
db.posts.find({
  comments: {
    $elemMatch: {
      user: 'Mary Williams'
    }
  }
})

// search matched element
db.posts.find({
  $text: {
    $search: "\"Post O\""
  }
})

// find greater than (gt)
db.posts.find({
  views: {
    gt: 6
  }
})
