#include <narwhal.h>
#include <nfa.h>

TEST(NFA_CREATE) {
	NFA n = new_NFA(8);
	ASSERT(n != NULL, "Unable to create NFA");
}
