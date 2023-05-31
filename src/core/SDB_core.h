//
// Semantic DB 4
// Created 2023/5/31
// Updated 2023/5/31
// Author Garry Morrison
// License GPL v3
//

// The includes needed for the core SDB library:

#pragma once


#include "../Function/SplitJoin.h"
#include "../KetMap/KetMap.h"
#include "../FunctionOperatorMap/FunctionOperatorMap.h"
#include "../OperatorUsageMap/OperatorUsageMap.h"
// #include "src/Function/CoutRedirect.h"
#include "../Function/Timer.h"


// Core library includes:
#include "../KetMap/KetMap.h"
#include "../Sequence/Ket.h"
#include "../Sequence/Superposition.h"
#include "../Sequence/Sequence.h"
#include "../Context/Frame.h"
#include "../Context/NewContext.h"
#include "../Context/ContextList.h"
#include "../Operator/SimpleOperator.h"
#include "../Operator/NumericOperator.h"
#include "../Operator/PoweredOperator.h"
#include "../Operator/OperatorSequence.h"
#include "../OperatorLibrary/SigmoidLibrary.h"
#include "../FunctionOperatorMap/FunctionOperatorMap.h"
#include "../Operator/BracketOperator.h"
#include "../CompoundConstant/ConstantInteger.h"
#include "../CompoundConstant/ConstantFloat.h"
#include "../CompoundConstant/ConstantOperator.h"
#include "../CompoundConstant/ConstantString.h"
#include "../Operator/CompoundOperator.h"
#include "../Sequence/OperatorWithSequence.h"
#include "../Sequence/SelfKet.h"
#include "../Operator/EmptyOperator.h"
#include "../OperatorLibrary/OperatorLibrary.h"
#include "../OperatorLibrary/FunctionOperatorLibrary.h"
#include "../Function/misc.h"
#include "../Function/Timer.h"
#include "../Operator/FunctionOperator.h"
#include "../Sequence/LearnRule.h"
#include "../Sequence/MultiLearnRule.h"
#include "../Sequence/MultiSelfKet.h"
#include "../Parser/Driver.h"
#include "../OperatorUsageMap/OperatorUsageMap.h"
// #include "DocsGenerator/DocsGenerator.h"
#include "../Sequence/IfElseStatement.h"
#include "../Sequence/ForStatement.h"
#include "../Sequence/WhileStatement.h"
#include "../OperatorLibrary/TMOperatorLibrary.h"