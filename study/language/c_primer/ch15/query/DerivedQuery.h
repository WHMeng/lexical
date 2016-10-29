class WordQuery : public Query_base{
	friend class Query; // Query uses the WordQuery constructor
	WordQuery(const std::string &s) query_word(s) {}
	std::set<line_no> eval(const TextQuery &t) const{
		return t.run_query(query_word);
	}
	std::ostream &display(std::ostream &os) const{
		return os << query_word;
	}
	std::string query_word;
};

class NotQuery : public Query_base{
	friend Query operator~(const Query &);
	NotQuery(Query q) : query(q) {}
	std::set<line_no> eval(const TextQuery &) const;
	std::ostream &display(std::ostream &os) const{
		return os << "~(" << query << ")";
	}
	const Query query;
};

class BinaryQuery : public Query_base{
protected:
	BinaryQuery(Query left, Query right, std::string op)
		: lhs(left), rhs(right), oper(op) {}
	std::ostream &display(std::ostream &os) const{
		return os << "(" << lhs << " " << oper << " " << rhs << ")";
	}
	const Query lhs, rhs;
	const std::string oper;
};

class AndQuery : public BinaryQuery{
	friend Query operator&(const Query &, const Query &);
	AndQuery(Query left, Query right)
		: BinaryQuery(left, right, "&") {}
	std::set<line_no> eval(const TextQuery &) const;
};

class OrQuery : public BinaryQuery{
	friend Query operator|(const Query &, const Query &);
	OrQuery(Query left, Query right)
		: BinaryQuery(left, right, "|") {}
	std::set<line_no> eval(const TextQuery &) const;
};
