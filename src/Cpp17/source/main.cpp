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
}