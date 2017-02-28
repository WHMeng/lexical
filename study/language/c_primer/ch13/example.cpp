
class Message {
public:
	// folders is initialized to the empty set automatically
	Message(const std::string &str = "")
		: contents(str) {}
	Message(const Message &);
	Message &operator=(const Message &);
	~Message();
	void save(Folder &);
	void remove(Folder &);
private:
	std::string contents;
	std::set<Folder *> folders;
	void put_Msg_in_Folders(const std::set<Folder *> &);
	void remove_Msg_from_Folders();
};

Message::Message(const Message &m)
	: contents(m.contents)
	, folders(m.folders)
{
	// add this Message to each Folder that points to m
	put_Msg_in_Folders(folders);
}

void Message::put_Msg_in_Folders(const set<Folders *> &rhs){
	for(std::set<Folder *>::const_iterator beg = rhs.begin();
			beg != rhs.end(); ++beg){
		(*beg)->addMsg(this);
	}
}

Message &Message::operator=(const Message &rhs){
	if(&rhs != this){
		remove_Msg_from_Folders();
		contents = rhs.contents;
		folders = rhs.folders;
		put_Msg_in_Folders(rhs.folders);
	}
	return *this;
}

void Message::remove_Msg_from_Folders(){
	for(std::set<Folder *>::const_iterator beg = rhs.begin();
			beg != rhs.end(); ++beg){
		(*beg)->remMsg(this);
	}
}

Message::~Message(){
	remove_Msg_from_Folders();
}
