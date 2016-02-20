////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  [projectName]
//  File:     DataFlowNode.cpp (compile)
//  Authors:  Ofer Dekel
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DataFlowNode.h"

void DataFlowNode::SetFixedVariableName(const std::string & name)
{
    _fixedVariableName = name;
}

bool DataFlowNode::IsInitialized() const
{
    return _isInitialized;
}

void DataFlowNode::SetInitialized()
{
    _isInitialized = true;
}

bool DataFlowNode::HasTempVariableName() const
{
    if (_tempVariableIndex >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DataFlowNode::HasVariableName() const
{
    if (_fixedVariableName != "" || _tempVariableIndex >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string DataFlowNode::GetVariableName() const
{
    if (_fixedVariableName != "")
    {
        return _fixedVariableName;
    }
    else if (_tempVariableIndex >= 0)
    {
        return "tmp" + std::to_string(_tempVariableIndex);
    }
    else
    {
        throw std::runtime_error("this should never happen");
    }
}

uint64 DataFlowNode::GetTempVariableIndex() const
{
    if (_tempVariableIndex >= 0)
    {
        return (uint64)_tempVariableIndex;
    }
    else
    {
        throw std::runtime_error("this should never happen");
    }
}

void DataFlowNode::SetTempVariableIndex(uint64 index)
{
    _tempVariableIndex = (int)index;
}

bool DataFlowNode::HasActions() const
{
    if (_actions.empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

const std::vector<AddToAction>& DataFlowNode::GetActions() const
{
    return _actions;
}

std::vector<AddToAction>& DataFlowNode::GetActions()
{
    return _actions;
}

bool DataFlowNode::HasUncomputedInputs() const
{
    if (_numUncomputedInputs == 0)
    {
        return false;
    }
    {
        return true;
    }
}

void DataFlowNode::IncrementUncomputedInputs()
{
    ++_numUncomputedInputs;
}

void DataFlowNode::DecrementUncomputedInputs()
{
    --_numUncomputedInputs;
}

