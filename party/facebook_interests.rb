# Script to find shared interests and likes between a user and their friends
require 'rubygems'
require 'koala'

# Before running this script set the FACEBOOK_OAUTH_TOKEN env. variable.
oauth_token = ENV['FACEBOOK_OAUTH_TOKEN']
if !oauth_token
  puts "Please set the FACEBOOK_OAUTH_TOKEN environment variable"
  exit 1
end

if ARGV.length != 1
  puts "The first argument should be the name of the user"
  puts "Usage: #{$0} username"
  exit 1
else
  username = ARGV[0]
end

# Get a unique identifier for a connection graph object
# Note: names are not unique, so use the id field
def get_connection_ids(connections)
  connections.map { |connection| connection['id'] }
end

graph = Koala::Facebook::GraphAPI.new(oauth_token)

user_info = graph.get_object(username)
user_checkins = graph.get_connections(username, "checkins")

puts user_checkins.inspect

#user_likes = graph.get_connections(username, "likes")
#user_interests = graph.get_connections(username, "interests")
#user_likes_ids = get_connection_ids(user_likes)
#user_interests_ids = get_connection_ids(user_interests)
# Yay!  Built in set operations!
#user_likes_and_interests = user_likes_ids | user_interests_ids

# Get the user's friends
#friends = graph.get_connections(username, "friends")

#max = 0
#most_similar_friend = ""

# Loop through the friends, finding the intersection of their likes
#friends.each do |friend|
#  friend_likes = graph.get_connections(friend['id'], "likes")
#  friend_interests = graph.get_connections(friend['id'], "interests")
#  friend_likes_ids = get_connection_ids(friend_likes)
#  friend_interests_ids = get_connection_ids(friend_interests)
#  friend_likes_and_interests = friend_likes_ids | friend_interests_ids

#  intersection = user_likes_and_interests & friend_likes_and_interests

  # This will identify one (of possibly many) of the most similar friends
#  if intersection.count  > max
#    most_similar_friend = friend['name']
#    max = intersection.count
#  end

  #puts "intersection of likes between #{user_info['name']} and #{friend['name']} (#{intersection.count}): #{intersection.inspect}"
#end

#puts "Most similar friend: #{most_similar_friend}, count: #{max}"
