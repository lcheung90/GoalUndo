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

TEST(GoalUndoTest, testGetGoalAfterUndoSingleOperation)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Write buggy unit test");
  g.undoOperation();
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetGoalAfterUndoSingleOperationAlt)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Fork repo");
  g.addOperation(goalName,"Write buggy unit test");
  g.undoOperation();
  ASSERT_TRUE(g.getGoal() != "");
}

TEST(GoalUndoTest, testGetGoalAfterUnitOpGoalUndo)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName, "Write buggy unit test");
  g.undoGoal();
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetGoalAfterMultiOpGoalUndo)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Fork repo");
  g.addOperation("Write unit test");
  g.undoGoal();
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetGoalAfterMultiOpGoalUndoAlt)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Fork repo");
  g.addOperation("Write unit test");
  string altGoalName = "Start summer";
  g.addOperation(altGoalName,"Chill out");
  g.undoGoal();
  ASSERT_TRUE(g.getGoal() == goalName);
}

TEST(GoalUndoTest, testDefaultGoalNaming)
{
  GoalUndo g;
  g.addOperation("do something");
  ASSERT_TRUE(g.getGoal() == "do something");
}

TEST(GoalUndoTest, testEmptyStringDefaultGoalNaming)
{
  GoalUndo g;
  g.addOperation("");
  ASSERT_TRUE(g.getGoal() == "");
}
