//////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     CompareUtils.tcc (compare)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Neural-network-related
//

template <typename ValueType>
bool IsNeuralNetworkPredictorNode(const ell::model::Node* node)
{
    return dynamic_cast<const ell::nodes::NeuralNetworkPredictorNode<ValueType>*>(node) != nullptr;
}

template <typename ValueType>
bool IsNeuralNetworkLayerNode(const ell::model::Node* node)
{
    return dynamic_cast<const ell::nodes::NeuralNetworkLayerNodeBase<ValueType>*>(node) != nullptr;
}

template <typename ValueType>
bool HasNeuralNetworkPredictor(const ell::model::DynamicMap& map)
{
    static_assert(!std::is_integral<ValueType>::value, "Calling HasNeuralNetworkPredictor<T> with integral type!");
    auto& model = map.GetModel();
    auto nodeIter = model.GetNodeIterator();
    while (nodeIter.IsValid())
    {
        auto node = nodeIter.Get();
        if (IsNeuralNetworkPredictorNode<ValueType>(node))
        {
            return true;
        }
        nodeIter.Next();
    }
    return false;
}

template <typename ValueType>
ell::predictors::NeuralNetworkPredictor<ValueType> GetNeuralNetworkPredictor(ell::model::DynamicMap& map)
{
    throw ell::utilities::InputException(ell::utilities::InputExceptionErrors::invalidArgument, "Model must contain a neural network predictor");
}

//
// Report-writing
//
template <typename ValueType>
void WriteVector(const std::string& filename, const std::vector<ValueType>& vec) // dimensions?
{
    auto os = ell::utilities::OpenOfstream(filename);
    bool first = true;
    for (auto x : vec)
    {
        if (!first)
        {
            os << "\t";
        }

        if (std::is_same<ValueType, uint64_t>::value || std::is_same<ValueType, int64_t>::value)
        {
            auto oldWidth = os.width(sizeof(uint64_t) * 2 + 2);
            auto oldFill = os.fill('0');
            os << std::hex << x << std::dec;
            os.width(oldWidth);
            os.fill(oldFill);
        }
        else
        {
            os << x;
        }
        first = false;
    }
    os << "\n";
}

template <typename FunctionType>
void WriteStatsRow(std::ostream& reportStream, const VectorStatistics& layerStats, const VectorStatistics& nodeStats, const VectorStatistics& diffStats, const std::string& header, FunctionType getValueFunction)
{
    reportStream << "<tr> <td>" << header << "</td>";
    if (layerStats.IsValid())
    {
        reportStream << " <td>" << getValueFunction(layerStats) << "</td>";
    }
    if (nodeStats.IsValid())
    {
        reportStream << " <td>" << getValueFunction(nodeStats) << "</td>";
    }
    if (diffStats.IsValid())
    {
        reportStream << " <td>" << getValueFunction(diffStats) << "</td>";
    }
    reportStream << " </tr>\n";
}

