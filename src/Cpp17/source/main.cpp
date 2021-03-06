#include "new_features_cpp17/structural_binding.hpp"
#include "new_features_cpp17/variable_range_limitation.hpp"
#include "new_features_cpp17/way_of_initialization.hpp"
#include "new_features_cpp17/automatic_template.hpp"
#include "new_features_cpp17/constexpr-if.hpp"
#include "new_features_cpp17/inline_static_class.hpp"
#include "new_features_cpp17/folding.hpp"

#include "vector/vector.h"
#include "map/map.h"
#include "unordered_map/unordered_map.h"
#include "stack/stack.h"
#include "set/set.h"
#include "multimap/multimap.h"
#include "queue/queue.h"
#include "iterators/iterators.h"
#include "lambda/lambda.h"
#include "algorithms/algorithms.h"
#include "advanced_algorithms/advanced_algorithms.h"
#include "strings/strings.h"
#include "traits/traits.h"
#include "parallel_processing/parallell_processing.h"
#include "file_systems/file_systems.h"

int main(void)
{
    structural_binding_example();
    varaible_range_limitation_example();
    way_of_initialization_example();
    automatic_template_types_deduction_example();
    constexpr_if_example();

    // Inline static class example
    cout << "Inline static class example \n\n";
    cout << "using inline header-only class property: value: " << oInlineClass.variable << endl;

    fold_example();

    vector_example();

    map_example();

    unordered_map_example();

    stack_example();

    set_example();

    multimap_example();

    queue_example();

    iterators_example();

    lambda_example();

    algorithms_example();

    advanced_algorithms_example();

    strings_example();

    traits_example();

    parallell_processing_example();

    file_systems_example();
}