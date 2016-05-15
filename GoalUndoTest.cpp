/**
 * Unit Tests for GoalUndo class
**/

#include <gtest/gtest.h>
#include "GoalUndo.h"
using namespace std;

class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(GoalUndoTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(GoalUndoTest, testGetGoalNoGoal)
{
  GoalUndo g;
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetGoalWithGoal)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Write unit test");
  ASSERT_TRUE(g.getGoal() == goalName);
}
