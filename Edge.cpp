#include "Edge.h"


double getLineCircleIntersection(double x0, double y0, double x1, double y1, double centerX, double centerY, double radius)
{
	double a = (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
	double b = 2 * (x1 - x0) * (x0 - centerX) + 2 * (y1 - y0) * (y0 - centerY);
	double c = (x0 - centerX) * (x0 - centerX) + (y0 - centerY) * (y0 - centerY) - radius * radius;

	double check = std::sqrt(b * b - 4 * a * c);

	if (check < 0)
	{
		log("LOL");
		return 0;
	}
	double t = ((double)2 * c) / (-b + check);

	/*if (t < 0 || t > 1)
	{
		log("LOl2" << " " << t);
		return 0;
	}*/
	return std::abs(t);
}

sf::Vector2f pointOnVector(double x0, double y0, double x1, double y1, double t)
{
	return sf::Vector2f(static_cast<float>((x1 - x0) * t + x0), static_cast<float>((y1 - y0) * t + y0));
}

double distanceBetweenTwoPoints(double x0, double y0, double x1, double y1)
{
	return std::sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}

Edge::Edge(Node* node1, Node* node2, float weight) : weight(weight)
{
	this->nodes.node1 = node1;
	this->nodes.node2 = node2;

	this->shape.line = new sf::VertexArray(sf::Lines, 2);
	this->shape.font = new sf::Font();
	this->shape.font->loadFromFile(FIRA_CODE_FONT);
	this->shape.weightText = new sf::Text();
	this->shape.weightText->setFont(*this->shape.font);
	this->shape.weightText->setCharacterSize(EDGE_WEIGHT_FONT_SIZE);
	this->shape.weightText->setFillColor(WHITE);

	double t1 = getLineCircleIntersection(node1->getCenter().x, node1->getCenter().y, node2->getCenter().x, node2->getCenter().y, node1->getCenter().x, node1->getCenter().y, node1->getCircleShape().getRadius());
	double t2 = getLineCircleIntersection(node1->getCenter().x, node1->getCenter().y, node2->getCenter().x, node2->getCenter().y, node2->getCenter().x, node2->getCenter().y, node2->getCircleShape().getRadius());
	(*this->shape.line)[0].position = pointOnVector(node1->getCenter().x, node1->getCenter().y, node2->getCenter().x, node2->getCenter().y, t1);
	(*this->shape.line)[1].position = pointOnVector(node1->getCenter().x, node1->getCenter().y, node2->getCenter().x, node2->getCenter().y, t2);

	sf::Vector2f midPoint = sf::Vector2f((node1->getCenter().x + node2->getCenter().x) / 2, (node1->getCenter().y + node2->getCenter().y) / 2);
	this->shape.weightText->setString(std::to_string((int)this->weight));
	this->shape.weightText->setPosition(midPoint);
	
	for (unsigned int i = 0; i < 2; i++)
	{
		(*this->shape.line)[i].color = WHITE;
	}
	float x0 = (*this->shape.line)[0].position.x;
	float y0 = (*this->shape.line)[0].position.y;
	float x1 = (*this->shape.line)[1].position.x;
	float y1 = (*this->shape.line)[1].position.y;
	this->shape.arrow = Arrow(x0, y0, x1, y1);

}

Edge::~Edge()
{
	delete (this->shape.line);
	delete (this->shape.font);
	delete (this->shape.weightText);
}


void Edge::updatePosition()
{

	double t1 = getLineCircleIntersection(this->nodes.node1->getCenter().x, this->nodes.node1->getCenter().y, this->nodes.node2->getCenter().x, this->nodes.node2->getCenter().y, this->nodes.node1->getCenter().x, this->nodes.node1->getCenter().y, this->nodes.node1->getCircleShape().getRadius());
	double t2 = getLineCircleIntersection(this->nodes.node1->getCenter().x, this->nodes.node1->getCenter().y, this->nodes.node2->getCenter().x, this->nodes.node2->getCenter().y, this->nodes.node2->getCenter().x, this->nodes.node2->getCenter().y, this->nodes.node2->getCircleShape().getRadius());
	(*this->shape.line)[0].position = pointOnVector(this->nodes.node1->getCenter().x, this->nodes.node1->getCenter().y, this->nodes.node2->getCenter().x, this->nodes.node2->getCenter().y, t1);
	(*this->shape.line)[1].position = pointOnVector(this->nodes.node1->getCenter().x, this->nodes.node1->getCenter().y, this->nodes.node2->getCenter().x, this->nodes.node2->getCenter().y, t2);

	sf::Vector2f midPoint = sf::Vector2f((this->nodes.node1->getCenter().x + this->nodes.node2->getCenter().x) / 2, (this->nodes.node1->getCenter().y + this->nodes.node2->getCenter().y) / 2);
	float x0 = (*this->shape.line)[0].position.x;
	float y0 = (*this->shape.line)[0].position.y;
	float x1 = (*this->shape.line)[1].position.x;
	float y1 = (*this->shape.line)[1].position.y;
	this->shape.weightText->setPosition(midPoint);
	this->shape.arrow.update(x0, y0, x1, y1);
}

const Nodes Edge::getNodes() const
{
	return this->nodes;
}

const sf::VertexArray& Edge::getVertexArray() const
{
	return *this->shape.line;
}

const sf::Text& Edge::getWeightText() const
{
	return *this->shape.weightText;
}

const Arrow& Edge::getArrow() const
{
	return this->shape.arrow;
}
EdgeCollection::EdgeCollection()
{
	
}

EdgeCollection::~EdgeCollection()
{
	for (unsigned int i = 0; i < this->edges.size(); i++)
	{
		delete (this->edges[i]);
	}
}

void EdgeCollection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& edge : this->edges)
	{
		edge->updatePosition();
		target.draw(edge->getVertexArray());
		if (this->directed)
		{
			target.draw(edge->getArrow());
		}
		if (this->weighted)
		{
			target.draw(edge->getWeightText());
		}
	}
}

void EdgeCollection::addEdge(Node* node1, Node* node2, float weight)
{
	Edge* edge = new Edge(node1, node2, weight);
	this->edges.push_back(edge);
}


Arrow::Arrow(float x0, float y0, float x1, float y1)
{
	this->halfArrow = sf::VertexArray(sf::Triangles, 3);
	this->halfArrow2 = sf::VertexArray(sf::Triangles, 3);
	sf::Vector2f vector(x1 - x0, y1 - y0);

	double t = 45 / distanceBetweenTwoPoints(x0, y0, x1, y1);
	sf::Vector2f midPoint = pointOnVector(x0, y0, x1, y1, 1 - t);

	sf::Vector2f pointPrepOnVec = pointOnVector(x0, y0, x1, y1, 1 - (t * 1.5));


	sf::Vector2f vecTemp = sf::Vector2f(x1 - pointPrepOnVec.x, y1 - pointPrepOnVec.y);

	sf::Vector2f prep1 = sf::Vector2f(-vecTemp.y, vecTemp.x);
	sf::Vector2f prep2 = sf::Vector2f(vecTemp.y, -vecTemp.x);

	sf::Vector2f pointOnPrep1 = sf::Vector2f(pointPrepOnVec.x + 0.25f * prep1.x, pointPrepOnVec.y + 0.25f * prep1.y);
	sf::Vector2f pointOnPrep2 = sf::Vector2f(pointPrepOnVec.x + 0.25f * prep2.x, pointPrepOnVec.y + 0.25f * prep2.y);

	this->halfArrow[0].position = sf::Vector2f(x1, y1);
	this->halfArrow[1].position = midPoint;
	this->halfArrow[2].position = pointOnPrep1;
	
	this->halfArrow2[0].position = sf::Vector2f(x1, y1);
	this->halfArrow2[1].position = midPoint;
	this->halfArrow2[2].position = pointOnPrep2;

	this->halfArrow[0].color = RED;
	this->halfArrow[1].color = BLUE;
	this->halfArrow[2].color = GREEN;

	this->halfArrow2[0].color = RED;
	this->halfArrow2[1].color = BLUE;
	this->halfArrow2[2].color = GREEN;
}

Arrow::Arrow()
{
}


Arrow::~Arrow()
{

}


void Arrow::update(float x0, float y0, float x1, float y1)
{
	sf::Vector2f vector(x1 - x0, y1 - y0);

	double t = 45 / distanceBetweenTwoPoints(x0, y0, x1, y1);
	sf::Vector2f midPoint = pointOnVector(x0, y0, x1, y1, 1 - t);

	sf::Vector2f pointPrepOnVec = pointOnVector(x0, y0, x1, y1, 1 - (t * 1.2));


	sf::Vector2f vecTemp = sf::Vector2f(x1 - pointPrepOnVec.x, y1 - pointPrepOnVec.y);
	sf::Vector2f prep1 = sf::Vector2f(-vecTemp.y, vecTemp.x);
	sf::Vector2f prep2 = sf::Vector2f(vecTemp.y, -vecTemp.x);

	sf::Vector2f pointOnPrep1 = sf::Vector2f(pointPrepOnVec.x + 0.25f * prep1.x, pointPrepOnVec.y + 0.25f * prep1.y);
	sf::Vector2f pointOnPrep2 = sf::Vector2f(pointPrepOnVec.x + 0.25f * prep2.x, pointPrepOnVec.y + 0.25f * prep2.y);

	this->halfArrow[0].position = sf::Vector2f(x1, y1);
	this->halfArrow[1].position = midPoint;
	this->halfArrow[2].position = pointOnPrep1;

	this->halfArrow2[0].position = sf::Vector2f(x1, y1);
	this->halfArrow2[1].position = midPoint;
	this->halfArrow2[2].position = pointOnPrep2;

	
}


void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->halfArrow);
	target.draw(this->halfArrow2);
}