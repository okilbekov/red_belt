#include <algorithm>
#include <string>
#include <unordered_set>

#include "test_runner.h"
#include "profile.h"

using namespace std;

class Learner {
 private:
	unordered_set<string> dict;

 public:
	int Learn(const vector<string>& words) {
		int newWords = 0;
		for (const auto& word : words) {
			if(dict.count(word) == 0) {
				dict.insert(word);
				++newWords;
			}
		}
		return newWords;
	}

	vector<string> KnownWords() {
		vector<string> result = {dict.begin(), dict.end()};
		sort(result.begin(), result.end());
		return result;
	}
};

void TestAllDifferent() {
	LOG_DURATION("20'000 words total")
	Learner learner;
	vector<string> words;
	for(int i = 0; i < 20000; ++i) {
		words.push_back(to_string(i));
	}

	{
		LOG_DURATION("Learn")
		learner.Learn(words);
	}

	{
		LOG_DURATION("KnownWords")
		ASSERT_EQUAL(learner.KnownWords().size(), 20000)
	}
	sort(words.begin(), words.end());
	ASSERT_EQUAL(learner.KnownWords(), words);
}

void TestAllEqual() {
	LOG_DURATION("20'000 words total")
	Learner learner;
	vector<string> words;
	for(int i = 0; i < 20000; ++i) {
		words.push_back("1234");
	}

	{
		LOG_DURATION("Learn")
		learner.Learn(words);
	}

	{
		LOG_DURATION("KnownWords")
		ASSERT_EQUAL(learner.KnownWords().size(), 1)
	}
}

void TestFromCoursera() {
	Learner learner;

	ASSERT_EQUAL(learner.Learn({"hello"}), 1);

	ASSERT_EQUAL(learner.Learn({"hello", "world"}), 1);

	ASSERT_EQUAL(learner.Learn({"good", "bye", "world", "good", "bye"}), 2);

	ASSERT_EQUAL(learner.KnownWords(), vector<string>({"bye", "good", "hello", "world"}));
}

int main() {
	TestRunner tr;
	// RUN_TEST(tr, TestAllDifferent);
	// cout << endl;
	// RUN_TEST(tr, TestAllEqual);

	RUN_TEST(tr, TestFromCoursera);
}