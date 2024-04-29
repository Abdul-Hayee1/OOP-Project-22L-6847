#include "Memory.h"

Memory::Memory(Post* origPostPtr, string PostID, Date* PublishedDate, string Description, string* UsersWhoLiked, int NoOfLikes, Activity* activity, string OwnerID, Comment** comments, int CommentCount)
    : Post(PostID, PublishedDate, Description,activity,OwnerID, UsersWhoLiked, NoOfLikes), MemoryOfPost(origPostPtr) {}

Memory::~Memory()
{

}   