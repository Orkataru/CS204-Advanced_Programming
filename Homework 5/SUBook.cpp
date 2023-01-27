// Written by Bilgehan Bilgin || 00030902

#include "SUBook.h"
#include <string>
using namespace std;

// Constructor for the User class
User::User(string name) {
	this->name = name;
	num_comments = 0;
}

// Destructor for the User class that deletes User objects along with their Posts and Comments
User::~User() {
	// Delete all posts of the user
	for (int i = 0; i < posts.size(); i++)
	{
		posts[i].~Post();
	}
}

// Creates a new post with the given content and returns its reference
Post& User::createPost(string content) {
	posts.push_back(Post(*this, content));
	return posts[posts.size() - 1];
}

// Returns a vector of Post pointers pointing to the User's posts
vector<Post*> User::getPosts() {

	vector<Post*> ptr_vector(posts.size());
	for (int i = 0; i < posts.size(); i++)
	{
		ptr_vector[i] = &posts[i];
	}

	return ptr_vector;
}

// Getter function that returns the number of comments the User has made
int User::getNumComments() {
	return num_comments;
}

// Getter function that returns the name of the User
string User::getName() {
	return name;
}

// Post constructor
Post::Post(User& user, string& content) : user(user), content(content) {};

// Copy constructor for Post class
Post::Post(const Post& post) : user(post.user), content(post.content) {
	comments = post.comments;
};

Post Post::operator=(const Post& rhs) {
	if (this == &rhs)
	{
		return *this;
	}
	else
	{
		user = rhs.user;
		comments = rhs.comments;
		content = rhs.content;
	}
	return *this;
}

// Deallocate the space kept by the Post object
Post::~Post() {}	// The destructor automatically deallocates the space used up by Post objects (including their member variables),
// so no need to do anything else

// Creates new Comment with the given parameters
void Post::addComment(string content, User* commenter) {
	// add the new comment to the vector containing the comments of this post
	this->comments.push_back(Comment(*commenter, *this, content));


	// Increment the comment num of the user
	commenter->num_comments++;

}

// Returns a vector of Comment pointers that point to the comments of the Post
vector<Comment*> Post::getComments() {

	vector<Comment*> ptr_vector(comments.size());

	for (int i = 0; i < ptr_vector.size(); i++)
	{
		ptr_vector[i] = &comments[i];
	}

	return ptr_vector;
}

// Getter function that returns a reference to the User
User& Post::getUser() {
	return user;
}

// Getter function that returns the content of the Post as a string
string Post::getContent() {
	return this->content;
}

// Constructor for the Comment class
Comment::Comment(User& user, Post& post, string& content) : user(user), post(post), content(content) {}

// Copy constructor for the Comment Class
Comment::Comment(const Comment& comment) : user(comment.user), post(comment.post), content(comment.content) {
	// In order to counter the unwanted effect of the Comment destructor during Post::addComment(),
	// increment num_comments by 1
	comment.user.num_comments++;
}

Comment Comment::operator=(const Comment& rhs) {
	if (this == &rhs)
	{
		return *this;
	}
	else
	{
		user = rhs.user;
		post = rhs.post;
		content = rhs.content;
	}
	return *this;
}

// Destructor for the Comment class
Comment::~Comment() {
	// Decrement the # of comments made by the user by 1
	this->user.num_comments -= 1;
}

// Getter function that returns a reference to the User
User& Comment::getUser() {
	return this->user;
}

// Getter function that returns the content of the Comment
string Comment::getContent() {
	return content;
}

// Getter function that returns a reference to the Post the Comment is on
Post& Comment::getPost() {
	return post;
}