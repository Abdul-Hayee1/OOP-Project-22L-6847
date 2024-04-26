#ifndef MEMORY_H
#define MEMORY_H

#include "Post.h"

using namespace std;

class Post;

class Memory : public Post {
	Post* MemoryOfPost;
public:
	/*Memory();*/
	Memory(Post*, string, Date*,string,string*,int, Activity*,string,Comment**, int);

	~Memory();
};

#endif