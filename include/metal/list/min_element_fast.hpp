#ifndef METAL_LIST_MIN_ELEMENT_FAST_HPP
#define METAL_LIST_MIN_ELEMENT_FAST_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/lambda.hpp"
#include "../list/list.hpp"
#include "../number/if.hpp"

namespace metal {
    namespace fast {
        namespace detail {

            template<bool done = false>
            struct _min_element_worker;

            template<>
            struct _min_element_worker<false> {
                template<
                    template<class...> class comp, class v0, class v1,
                    class... tail>
                using type = typename _min_element_worker<!sizeof...(tail)>::
                    template type<comp, if_<comp<v1, v0>, v1, v0>, tail...>;
            };

            template<>
            struct _min_element_worker<true> {
                template<template<class...> class comp, class v0>
                using type = v0;
            };

            template<class seq>
            struct _min_element_impl {};

            template<class v0, class... tail>
            struct _min_element_impl<list<v0, tail...>> {
                template<template<class...> class comp>
                using type = typename _min_element_worker<!sizeof...(
                    tail)>::template type<comp, v0, tail...>;
            };

            template<
                class v0, class v1, class v2, class v3, class v4, class v5,
                class v6, class v7, class v8, class v9, class v10, class v11,
                class v12, class v13, class v14, class v15, class v16,
                class v17, class v18, class v19, class v20, class v21,
                class v22, class v23, class v24, class v25, class v26,
                class v27, class v28, class v29, class v30, class v31,
                class v32, class v33, class v34, class v35, class v36,
                class v37, class v38, class v39, class v40, class v41,
                class v42, class v43, class v44, class v45, class v46,
                class v47, class v48, class v49, class v50, class v51,
                class v52, class v53, class v54, class v55, class v56,
                class v57, class v58, class v59, class v60, class v61,
                class v62, class v63, class v64, class v65, class v66,
                class v67, class v68, class v69, class v70, class v71,
                class v72, class v73, class v74, class v75, class v76,
                class v77, class v78, class v79, class v80, class v81,
                class v82, class v83, class v84, class v85, class v86,
                class v87, class v88, class v89, class v90, class v91,
                class v92, class v93, class v94, class v95, class v96,
                class v97, class v98, class v99, class... tail>
            struct _min_element_impl<list<
                v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14,
                v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27,
                v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40,
                v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53,
                v54, v55, v56, v57, v58, v59, v60, v61, v62, v63, v64, v65, v66,
                v67, v68, v69, v70, v71, v72, v73, v74, v75, v76, v77, v78, v79,
                v80, v81, v82, v83, v84, v85, v86, v87, v88, v89, v90, v91, v92,
                v93, v94, v95, v96, v97, v98, v99, tail...>> {
                template<template<class...> class comp>
                using type = metal::detail::forward<
                    _min_element_impl<list<
                        typename _min_element_worker<false>::template type<
                            comp,
                            typename _min_element_worker<false>::template type<
                                comp, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9>,
                            typename _min_element_worker<false>::template type<
                                comp, v10, v11, v12, v13, v14, v15, v16, v17,
                                v18, v19>,
                            typename _min_element_worker<false>::template type<
                                comp, v20, v21, v22, v23, v24, v25, v26, v27,
                                v28, v29>,
                            typename _min_element_worker<false>::template type<
                                comp, v30, v31, v32, v33, v34, v35, v36, v37,
                                v38, v39>,
                            typename _min_element_worker<false>::template type<
                                comp, v40, v41, v42, v43, v44, v45, v46, v47,
                                v48, v49>,
                            typename _min_element_worker<false>::template type<
                                comp, v50, v51, v52, v53, v54, v55, v56, v57,
                                v58, v59>,
                            typename _min_element_worker<false>::template type<
                                comp, v60, v61, v62, v63, v64, v65, v66, v67,
                                v68, v69>,
                            typename _min_element_worker<false>::template type<
                                comp, v70, v71, v72, v73, v74, v75, v76, v77,
                                v78, v79>,
                            typename _min_element_worker<false>::template type<
                                comp, v80, v81, v82, v83, v84, v85, v86, v87,
                                v88, v89>,
                            typename _min_element_worker<false>::template type<
                                comp, v90, v91, v92, v93, v94, v95, v96, v97,
                                v98, v99>>,
                        tail...>>::template type,
                    comp>;
            };

            template<class lbd>
            struct _min_element {};

            template<template<class...> class comp>
            struct _min_element<lambda<comp>> {
                template<class seq>
                using type = metal::detail::forward<
                    _min_element_impl<seq>::template type, comp>;
            };

        } // detail

        template<class seq, class lbd>
        using min_element =
            metal::detail::call<detail::_min_element<lbd>::template type, seq>;
    } // slow
} // metal

#endif
