#pragma once

#include <string>
#include <vector>

using namespace std;

class Comment;
class Post;


class User {
private:
	string name;
	vector<Post> posts;
	int num_comments;
public:
	User(string);
	~User();
	Post& createPost(string content);
	vector<Post*> getPosts();
	int getNumComments();
	string getName();
	friend Comment;
	friend Post;
};

class Post {
private:
	User& user;
	string content;
	vector<Comment> comments;
public:
	Post(User&, string&);
	~Post();
	Post(const Post&);
	void addComment(string content, User* commenter);
	vector<Comment*> getComments();
	User& getUser();
	string getContent();
	Post operator=(const Post&);
	friend Comment;
	friend User;
};

class Comment {
private:
	User& user;
	Post& post;
	string content;
public:
	Comment(User&, Post&, string&);
	~Comment();
	Comment(const Comment&);
	User& getUser();
	string getContent();
	Post& getPost();
	Comment operator=(const Comment&);
	friend Post;
	friend User;
};

