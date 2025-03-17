package main

import (
	"context"
	"fmt"
	"math/rand"
	"time"

	"github.com/user/alternative_route/router"
	"github.com/user/alternative_route/service"
)

func init() {
	// In Go 1.20+, there's no need to seed the global random source explicitly
	// For older Go versions, this would be needed:
	// rand.Seed(time.Now().UnixNano())

	// For Go 1.20+, we can simply initialize a new random source
	rand.New(rand.NewSource(time.Now().UnixNano()))
}

func main() {
	// Create a mock router
	mockRouter := router.NewMockRouter()

	// Create an alternative route service
	alternativeService := service.NewAlternativeRouteService(mockRouter)

	// Define locations for route calculation
	startPoints := []string{"New York", "Los Angeles", "Chicago", "Houston", "Phoenix"}
	endPoints := []string{"Miami", "Seattle", "Boston", "Denver", "Atlanta"}

	// Create context
	ctx := context.Background()

	// Process multiple requests
	for i := 0; i < 3; i++ {
		// Select random start and end points
		startIndex := rand.Intn(len(startPoints))
		endIndex := rand.Intn(len(endPoints))

		// Ensure start and end points are different
		if startIndex == endIndex {
			endIndex = (endIndex + 1) % len(endPoints)
		}

		startPoint := startPoints[startIndex]
		endPoint := endPoints[endIndex]

		fmt.Printf("\n\n=== Finding routes from %s to %s ===\n", startPoint, endPoint)

		// Create request
		req := service.AlternativeRouteRequest{
			StartPoint:      startPoint,
			EndPoint:        endPoint,
			NumAlternatives: 3,
			Variations:      []string{"fastest", "shortest", "scenic"},
		}

		// Call the alternative route service
		result, err := alternativeService.GetAlternativeRoute(ctx, req)
		if err != nil {
			fmt.Printf("Error getting alternative routes: %v\n", err)
			continue
		}

		// Display results
		fmt.Printf("Found %d alternative routes (took %v):\n", len(result.Routes), result.TotalDuration)
		for i, route := range result.Routes {
			fmt.Printf("\nRoute %d:\n", i+1)
			fmt.Printf("  From: %s\n", route.StartPoint)
			fmt.Printf("  To: %s\n", route.EndPoint)
			fmt.Printf("  Distance: %.2f km\n", route.Distance)
			fmt.Printf("  Duration: %v\n", route.Duration)
			fmt.Printf("  Description: %s\n", route.Description)
		}
	}
}
